#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <SDL3_image/SDL_image.h>

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned long int deltaTime;
} AppState;

int SDL_AppInit(void **appstate, int argc, char **argv) {
    // Ignores argc and argv without compiler complaining
    (void)argc;
    (void)argv;

    const int windowWidth = 640;
    const int windowHeight = 480;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        SDL_Log("SDL_Init failed (%s)\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *as = malloc(sizeof(AppState));
    *appstate = as;

    if (SDL_CreateWindowAndRenderer("Window", windowWidth, windowHeight, 0,
                                    &as->window, &as->renderer) < 0) {
        SDL_Log("SDL_CreateWindowAndRenderer failed (%s)\n", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_Log("IMG_Init failed (%s)\n", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    as->deltaTime = 0;

    return SDL_APP_CONTINUE;
}

int SDL_AppIterate(void *appstate) {
    AppState *as = (AppState *)appstate;
    unsigned long int startTime = SDL_GetTicks();

    SDL_Texture *box = IMG_LoadTexture(as->renderer, "build/assets/box.png");

    if (box == NULL) {
        SDL_Log("Failed to load box (%s)\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_FRect boxRect = {50, 50, 50, 50};

    SDL_RenderClear(as->renderer);
    SDL_SetRenderDrawColor(as->renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
    SDL_RenderTexture(as->renderer, box, NULL, &boxRect);
    SDL_RenderPresent(as->renderer);

    SDL_DestroyTexture(box);

    unsigned long int endTime = SDL_GetTicks();
    as->deltaTime = endTime - startTime;

    return SDL_APP_CONTINUE;
}

int SDL_AppEvent(void *appstate, const SDL_Event *event) {
    // AppState *as = (AppState *)appstate;
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate) {
    if (appstate == NULL) {
        return;
    }
    AppState *as = (AppState *)appstate;
    SDL_DestroyRenderer(as->renderer);
    SDL_DestroyWindow(as->window);
    free(as);
}
