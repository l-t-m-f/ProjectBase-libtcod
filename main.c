#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include <libtcod/libtcod.h>

static void init_game(TCOD_Context *ctxt, TCOD_Console *cnsl);
static void discard_args(int argc, char ** argv);

int main(int argc, char **argv)
{
    TCOD_Context ctxt = { 0 };

    TCOD_Console cnsl = { 0 };

    init_game(&ctxt, &cnsl);

    discard_args(argc, argv);

    return 0;
}
static void init_game(TCOD_Context *ctxt, TCOD_Console *cnsl)
{
    TCOD_ContextParams ctxt_params = 
    {
        .tcod_version = TCOD_COMPILEDVERSION,
        .pixel_width = 0,
        .pixel_height = 0,
        .columns = 120,
        .rows = 50,
        .renderer_type = TCOD_RENDERER_GLSL,
        .vsync = true,
        .window_title = "Test",
        .tileset = NULL,
        .argc = 0,
        .argv = NULL,
        .cli_output = NULL,
        .cli_userdata = NULL,
        .window_xy_defined = false
    };

     
    TCOD_Error err;
    err = TCOD_context_new(&ctxt_params, &ctxt);
    if(err < 0)
    {
        printf("Error: %s\n", TCOD_get_error());
        exit(EXIT_FAILURE);        
    }

    int c_rows = 0, c_cols = 0;
    TCOD_context_recommended_console_size(ctxt, 1.0f, &c_rows, &c_cols);

    *cnsl = (TCOD_Console) { .w = c_rows, .h = c_cols, .back = TCOD_blue, .elements =  (c_rows * c_cols) };
    cnsl->tiles = malloc(sizeof(TCOD_ConsoleTile) * 6000);

    TCOD_console_clear(cnsl);
    TCOD_console_draw_rect_rgb(cnsl, 5, 5, 10, 10, 'a', &TCOD_red, &TCOD_green, TCOD_BKGND_NONE);
    TCOD_context_present(ctxt, cnsl, NULL);

}

static void discard_args(int argc, char ** argv)
{
    char *capture[argc];
	for (int i = 0; i < argc; i++)
	{
		int c = 0;
		while(*(&argv[i] + c)){
			*(&capture[i] + c) = *(&argv[i] + c);
		}
	}
}
