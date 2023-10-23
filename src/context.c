#include "sorcery.h"

void contextStateClusterBuild(Context *ctx) {
    uint8 i;

    for (i = 0; i < 3; i++) {
        ctx->state.prevWallState.leftSegment[i] = false;
        ctx->state.prevWallState.rightSegment[i] = false;
    }
    
    ctx->state.gameRunning = true;
    ctx->state.quitPrompt = false;
    ctx->state.showMap = false;

    ctx->state.quitSelector = 0;
    ctx->state.choice = 0;
    ctx->state.input = 0;

    ctx->state.locale = English;
    ctx->state.gameState = Game;
}

void contextBuild(Context *ctx) {
    // Build the context

    playerBuild(&ctx->player);
    mazeBuild(&ctx->maze);
    consoleBufferBuild(&ctx->consoleBuffer);
    contextStateClusterBuild(ctx);
    ctx->player.position = ctx->maze.start;
}


void contextCleanUp(Context *ctx) {
    // Clean up the context
    consoleBufferCleanUp(&ctx->consoleBuffer);
}