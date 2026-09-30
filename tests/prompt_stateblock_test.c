/* Exercise the actual experimental submission against a fake D3D8 vtable.
   No graphics device, game process, DLL injection or hardware calls. */
#include "../src/prompt_render.c"
#undef NDEBUG
#include <assert.h>
static char logs[8192];
void analog_log_event(const char *s) { strncat(logs,s,sizeof logs-strlen(logs)-1); }
typedef struct { DWORD vs,ps,rs[256],ts[2][64]; IDirect3DBaseTexture8 *tex; unsigned stream; } FakeState;
static FakeState live,saved,before;
static unsigned creates,applies,deletes,draws,owned,next_token;
static int fail_create,fail_set,fail_draw,fail_apply,fail_delete;
static HRESULT STDMETHODCALLTYPE create(IDirect3DDevice8 *d,D3DSTATEBLOCKTYPE type,DWORD *token) {
 (void)d; assert(type==D3DSBT_ALL && !owned);creates++;
 if(fail_create)return E_FAIL;
 *token=++next_token;owned=*token;saved=live;return S_OK;
}
static HRESULT STDMETHODCALLTYPE apply(IDirect3DDevice8 *d,DWORD token) {
 (void)d; assert(token==owned);applies++;if(fail_apply)return E_FAIL;live=saved;return S_OK;
}
static HRESULT STDMETHODCALLTYPE del(IDirect3DDevice8 *d,DWORD token) {
 (void)d; assert(token==owned);deletes++;if(fail_delete)return E_FAIL;owned=0;return S_OK;
}
static HRESULT STDMETHODCALLTYPE vs(IDirect3DDevice8 *d,DWORD x) { (void)d; if(fail_set)return E_FAIL;live.vs=x;return S_OK; }
static HRESULT STDMETHODCALLTYPE ps(IDirect3DDevice8 *d,DWORD x) { (void)d; live.ps=x;return S_OK; }
static HRESULT STDMETHODCALLTYPE tex(IDirect3DDevice8 *d,DWORD stage,IDirect3DBaseTexture8 *t) { (void)d; assert(!stage);live.tex=t;return S_OK; }
static HRESULT STDMETHODCALLTYPE rs(IDirect3DDevice8 *d,D3DRENDERSTATETYPE key,DWORD x) { (void)d; assert(key<256);live.rs[key]=x;return S_OK; }
static HRESULT STDMETHODCALLTYPE ts(IDirect3DDevice8 *d,DWORD stage,D3DTEXTURESTAGESTATETYPE key,DWORD x) { (void)d; assert(stage<2 && key<64);live.ts[stage][key]=x;return S_OK; }
static HRESULT STDMETHODCALLTYPE draw(IDirect3DDevice8 *d,D3DPRIMITIVETYPE type,UINT count,const void *vertices,UINT stride) {
 (void)d; assert(type==D3DPT_TRIANGLELIST && count==2 && vertices && stride==sizeof(Vertex));draws++;live.stream=0;return fail_draw?E_FAIL:S_OK;
}
static IDirect3DDevice8Vtbl methods;
static IDirect3DDevice8 fake_device;
static unsigned char ctx[0x200];
static void enqueue(void) {
 queue[0]=(GlyphQuad){0x1234,0,6,1,2,3,4,0xffffffff};queued=1;
 current_context=(uintptr_t)ctx;current_valid=1;current_start=0;current_end=8;
 *(uintptr_t *)(ctx+0x1f0)=0x1234;
}
static void reset_case(void) {
 memset(&methods,0,sizeof methods);methods.CreateStateBlock=create;methods.ApplyStateBlock=apply;methods.DeleteStateBlock=del;
 methods.SetVertexShader=vs;methods.SetPixelShader=ps;methods.SetTexture=tex;methods.SetRenderState=rs;methods.SetTextureStageState=ts;methods.DrawPrimitiveUP=draw;
 fake_device.lpVtbl=&methods;device=&fake_device;texture=(IDirect3DTexture8 *)0x5678;metrics_ready=1;failed=0;draw_count=0;
 creates=applies=deletes=draws=owned=0;fail_create=fail_set=fail_draw=fail_apply=fail_delete=0;logs[0]=0;
 memset(&live,0x42,sizeof live);before=live;enqueue();
}
int main(void) {
 reset_case();pg_render_submit(ctx);assert(creates==1 && applies==1 && deletes==1 && draws==1 && !owned && !failed && !queued);
 assert(!memcmp(&live,&before,sizeof live));assert(strstr(logs,"state_deleted=1 lifecycle=per-submit"));
 enqueue();pg_render_submit(ctx);assert(creates==2 && applies==2 && deletes==2 && draws==2 && !owned && !failed);assert(!memcmp(&live,&before,sizeof live));
 reset_case();current_valid=0;pg_render_submit(ctx);assert(!creates && !deletes);
 reset_case();queue[0].array=0x9999;pg_render_submit(ctx);assert(!creates && !deletes);
 reset_case();fail_create=1;pg_render_submit(ctx);assert(creates==1 && !applies && !deletes && !owned && failed);assert(!memcmp(&live,&before,sizeof live));assert(strstr(logs,"CREATE FAILED hr=0x80004005"));
 reset_case();fail_set=1;pg_render_submit(ctx);assert(applies==1 && deletes==1 && !owned && !draws && failed);assert(!memcmp(&live,&before,sizeof live));
 reset_case();fail_draw=1;pg_render_submit(ctx);assert(applies==1 && deletes==1 && !owned && draws==1 && failed);assert(!memcmp(&live,&before,sizeof live));
 reset_case();fail_apply=1;pg_render_submit(ctx);assert(applies==1 && deletes==1 && !owned && failed);assert(strstr(logs,"apply=0x80004005 delete=0x00000000"));
 reset_case();fail_delete=1;pg_render_submit(ctx);assert(applies==1 && deletes==1 && owned && failed);assert(!memcmp(&live,&before,sizeof live));assert(strstr(logs,"delete=0x80004005"));
 reset_case();fail_apply=fail_delete=1;pg_render_submit(ctx);assert(applies==1 && deletes==1 && owned && failed);assert(strstr(logs,"apply=0x80004005 delete=0x80004005"));
 puts("PASS: 10 scenarios; per-submit ownership, full mocked state restoration, draw/set/create/apply/delete failures, cleanup attempts; no game opened.");return 0;
}
