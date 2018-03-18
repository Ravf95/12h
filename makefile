CC = gcc
SRCFILES =\
src/backend/main.c\
src/backend/f_/f_board.c\
src/backend/f_/f_fichas.c\
src/backend/f_/f_game.c\
src/backend/f_/f_log.c\
src/backend/f_/f_error.c\
src/backend/f_/f_rules.c\
src/backend/f_/f_mill.c\
src/backend/callback/callback_vtable_white.c\
src/backend/callback/callback_vtable_black.c\
src/backend/callback/callback_board.c\
src/backend/callback/callback_new_game.c\
src/backend/callback/callback_menubar.c\
src/backend/event/event_board_double_click.c\
src/backend/event/event_board_single_click.c\
src/backend/ia_/ia.c\
src/frontend/ui.c\
src/frontend/widget/w_window.c\
src/frontend/widget/w_board.c\
src/frontend/widget/w_vtable_white.c\
src/frontend/widget/w_vtable_black.c\
src/frontend/widget/w_status_bar.c\
src/frontend/widget/w_new_game.c\
src/frontend/widget/w_menubar.c\
src/frontend/widget/w_end_game.c\
src/frontend/widget/w_about.c

FLAGS = -Wall -ggdb -std=c11

BIN_NAME = bin/12h

H_DIRS =\
-I"src/frontend"\
-I"src/frontend/widget/headers"\
-I"src/backend"\
-I"src/backend/callback/headers"\
-I"src/backend/f_/headers"\
-I"src/backend/ia_/"\
`pkg-config --cflags gtk+-3.0`

LIBS_DIR = `pkg-config --libs gtk+-3.0`

bin/%.o: $(SRCFILES)
	gcc $(FLAGS) $(H_DIRS) -c $(SRCFILES) $(LIBS_DIR)

programa: bin/%.o
	$(CC) $(FLAGS) $(H_DIRS) -o $(BIN_NAME) *.o $(LIBS_DIR);\
	rm -f *.o
