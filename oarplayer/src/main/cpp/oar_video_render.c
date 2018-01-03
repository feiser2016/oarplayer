
#include <pthread.h>
#include <malloc.h>
#include "oar_video_render.h"

void oar_video_render_set_window(oar_video_render_context *ctx, struct ANativeWindow *window) {
    pthread_mutex_lock(ctx->lock);
    ctx->window = window;
    ctx->cmd |= CMD_SET_WINDOW;
    pthread_mutex_unlock(ctx->lock);
}


void oar_video_render_ctx_reset(oar_video_render_context * ctx){
    ctx->surface = EGL_NO_SURFACE;
    ctx->context = EGL_NO_CONTEXT;
    ctx->display = EGL_NO_DISPLAY;
    ctx->model = NULL;
    ctx->require_model_scale = 1;
    ctx->cmd = NO_CMD;
    ctx->draw_mode = wait_frame;
    ctx->require_model_rotation[0] = 0;
    ctx->require_model_rotation[1] = 0;
    ctx->require_model_rotation[2] = 0;
    ctx->width = ctx->height = 1;
}


oar_video_render_context *oar_video_render_ctx_create() {
    oar_video_render_context *ctx = malloc(sizeof(oar_video_render_context));
    ctx->lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(ctx->lock, NULL);
    ctx->set_window = oar_video_render_set_window;
    ctx->window = NULL;
    ctx->texture_window = NULL;
    oar_video_render_ctx_reset(ctx);
    return ctx;
}

void oar_video_render_ctx_release(oar_video_render_context *ctx) {
    pthread_mutex_destroy(ctx->lock);
    free(ctx->lock);
    free(ctx);
}