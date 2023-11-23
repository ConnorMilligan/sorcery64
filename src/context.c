#include "sorcery.h"

void contextBuild(Context *ctx) {
    // Build the context

    playerBuild(&ctx->player);
    enemyBuild(&ctx->enemy, 1);
    mazeBuild(&ctx->maze);
    consoleBufferBuild(&ctx->consoleBuffer);
    ctx->player.position = ctx->maze.start;

    ctx->gameRunning = true;

    ctx->quitPrompt = false;
    
    ctx->quitSelector = 0;
    ctx->choice = 0;
    ctx->input = 0;

    ctx->locale = English;
    //ctx->gameState = TitleScreen;
    ctx->gameState = DeathScreen;
    //ctx->gameState = Game;
}


void contextCleanUp(Context *ctx) {
    // Clean up the context
    consoleBufferCleanUp(&ctx->consoleBuffer);
}