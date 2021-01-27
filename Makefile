NAME = minishell
SRCS = srcs/input/process_input.c \
       srcs/input/prompt/put_prompt.c \
       srcs/input/prompt/get_dirname.c \
       srcs/input/prompt/get_hostname.c \
       srcs/input/tty_mode.c \
       srcs/input/t_char/cmd_end.c \
       srcs/input/t_char/update_col_row_t_char.c \
       srcs/input/t_char/t_char_update_size.c \
       srcs/input/t_char/find_next_cmd_tab_quote.c \
       srcs/input/t_char/new_t_char_elem.c \
       srcs/input/t_char/put_cmd_tab.c \
       srcs/input/t_char/cmd_tab_to_str.c \
       srcs/input/t_char/mid_t_char_elem.c \
       srcs/input/t_char/t_char_set_zeros.c \
       srcs/input/history/erase_displayed_cmd.c \
       srcs/input/history/history.c \
       srcs/input/free_input.c \
       srcs/input/events/jump_word_right.c \
       srcs/input/events/move_bot.c \
       srcs/input/events/process_clear_screen.c \
       srcs/input/events/move_home.c \
       srcs/input/events/move_bot_left.c \
       srcs/input/events/cut_word.c \
       srcs/input/events/move_end.c \
       srcs/input/events/move_left.c \
       srcs/input/events/paste_word.c \
       srcs/input/events/process_char.c \
       srcs/input/events/jump_word_left.c \
       srcs/input/events/move_top.c \
       srcs/input/events/move_right.c \
       srcs/input/events/process_del.c \
       srcs/input/events/move_top_right.c \
       srcs/input/events/copy_word.c \
       srcs/input/get_input.c \
       srcs/parser/quotes/update_quote_str.c \
       srcs/parser/quotes/update_single_quote_str.c \
       srcs/parser/quotes/find_next_index_jump_quotes.c \
       srcs/parser/quotes/ft_remove_empty_quotes.c \
       srcs/parser/quotes/ft_prev_quote.c \
       srcs/parser/quotes/update_double_quote_str.c \
       srcs/parser/quotes/ft_next_quote.c \
       srcs/parser/parser_cmd/create_argv.c \
       srcs/parser/parser_cmd/create_bin.c \
       srcs/parser/parser_cmd/create_redirection/create_stdout.c \
       srcs/parser/parser_cmd/create_redirection/create_stdin.c \
       srcs/parser/parser_cmd/create_redirection/redirection_filename.c \
       srcs/parser/parser_cmd/create_redirection/create_redirection.c \
       srcs/parser/parser_cmd/create_redirection/get_next_line/get_next_line_utils.c \
       srcs/parser/parser_cmd/create_redirection/get_next_line/get_next_line.c \
       srcs/parser/parser_cmd/create_redirection/create_stdin_double.c \
       srcs/parser/parser_cmd/create_redirection/create_stdin_simple.c \
       srcs/parser/parser_cmd/parser_cmd.c \
       srcs/parser/parser_cmd/create_builtin.c \
       srcs/parser/parser_cmd_chains.c \
       srcs/parser/parser_cmd_chain.c \
       srcs/parser/update_cmd_str/check_backslash.c \
       srcs/parser/update_cmd_str/check_quote.c \
       srcs/parser/update_cmd_str/put_surrounding_char.c \
       srcs/parser/update_cmd_str/check_wildcard/utils_wildcards.c \
       srcs/parser/update_cmd_str/check_wildcard/check_wildcard.c \
       srcs/parser/update_cmd_str/check_wildcard/expand_wildcards.c \
       srcs/parser/update_cmd_str/check_wildcard/update_wildcard.c \
       srcs/parser/update_cmd_str/check_chevron.c \
       srcs/parser/update_cmd_str/check_var.c \
       srcs/parser/update_cmd_str/update_cmd_str.c \
       srcs/parser/update_cmd_str/check_tilde.c \
       srcs/parser/free_parser.c \
       srcs/main.c \
       srcs/errors/syntax_error.c \
       srcs/errors/put_errors.c \
       srcs/errors/suffix_errors.c \
       srcs/errors/errors.c \
       srcs/core/forks_core.c \
       srcs/core/builtin/exit.c \
       srcs/core/builtin/unset.c \
       srcs/core/builtin/export.c \
       srcs/core/builtin/cd.c \
       srcs/core/builtin/builtin.c \
       srcs/core/signal.c \
       srcs/core/fds_core.c \
       srcs/core/core.c \
       srcs/core/env_vars.c \
       srcs/utils/ft_strjoin.c \
       srcs/utils/ft_memcpy.c \
       srcs/utils/ft_strcmp.c \
       srcs/utils/ft_memcpy8.c \
       srcs/utils/ft_strlcat.c \
       srcs/utils/ft_lstclear.c \
       srcs/utils/ft_atoi.c \
       srcs/utils/ft_split.c \
       srcs/utils/ft_strtrim.c \
       srcs/utils/ft_itoa.c \
       srcs/utils/ft_strlen.c \
       srcs/utils/ft_strdup.c \
       srcs/utils/ft_memset8.c \
       srcs/utils/ft_lstadd_back.c \
       srcs/utils/ft_alphanum.c \
       srcs/env/env.c \
       srcs/env/env_seek.c \
       srcs/env/get_env.c \
       srcs/env/del_env.c \
       srcs/env/set_env.c \
       srcs/gc_malloc/gc_open.c \
       srcs/gc_malloc/gc_rm_cb.c \
       srcs/gc_malloc/pool.c \
       srcs/gc_malloc/gc_exit.c \
       srcs/gc_malloc/lists.c \
       srcs/gc_malloc/gc_add_cb.c \
       srcs/gc_malloc/gc_free.c \
       srcs/gc_malloc/gc_close.c \
       srcs/gc_malloc/gc_malloc.c

OBJS = ${SRCS:.c=.o}
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
CC = clang
SEMB = assets/errors.bin
EMB = $(SEMB:.bin=.o)
SED = sed

all : $(NAME)

bonus : $(NAME)

$(NAME) : $(OBJS) $(EMB)
	$(CC) $(CFLAGS)	$(OBJS) -ltermcap $(EMB) -o $(NAME)

clean :
	$(RM) $(OBJS) $(EMB)

fclean : clean
	$(RM) $(NAME)

re : fclean all

$(OBJ) : %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EMB) : %.o: %.bin
	$(LD) -r -b binary $< -o $@
	$(SED) -i 's/_binary_assets_errors_bin_start/binary_assets_errors_bin_start_/g' $@

.PHONY: all clean fclean re bonus
