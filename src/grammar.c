#include "../includes/minishell.h"

int check_quotes()
{
	char	*temp;
	int		i;
	int		s;
	int		d;

	i = 0;
	s = 0;
	d = 0;
	temp = ft_strdup(_ms(0)->prompt);
	while (temp[i++])
	{
		if (temp[i] == '\'' && d % 2 == 0)
			s++;
		if (temp[i] == '\"' && s % 2 == 0)
			d++;
	}
	if (s % 2 != 0 || d % 2 != 0)
		return (ft_putstr_fd("minishell: parse error: Warning, string won't be processed, invalid number of quotes\n", 2), -1);
	return (1);
}

State transition_table[STATE_ERROR][TOKEN_COUNT] = {
    // CMD     ARG     PIPE    REDIR_OUT   FNM     UNKNOWN
    { STATE_AFTER_CMD, STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_ERROR },  // STATE_START
    { STATE_ERROR, STATE_AFTER_CMD, STATE_AFTER_PIPE, STATE_AFTER_REDIR, STATE_ERROR, STATE_ERROR },  // STATE_AFTER_CMD
    { STATE_AFTER_CMD, STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_ERROR },  // STATE_AFTER_PIPE
    { STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_ERROR, STATE_AFTER_CMD, STATE_ERROR },  // STATE_AFTER_REDIR
};

const char* token_type_to_string(TokenType type) {
    switch(type) {
        case TOKEN_CMD: return "CMD";
        case TOKEN_ARG: return "ARG";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_REDIR_OUT: return "REDIR_OUT";
        case TOKEN_FNM: return "FNM";
        case TOKEN_UNKNOWN: return "UNKNOWN";
        default: return "INVALID";
    }
}

const char* state_to_string(State state) {
    switch(state) {
        case STATE_START: return "START";
        case STATE_AFTER_CMD: return "AFTER_CMD";
        case STATE_AFTER_PIPE: return "AFTER_PIPE";
        case STATE_AFTER_REDIR: return "AFTER_REDIR";
        case STATE_ERROR: return "ERROR";
        default: return "INVALID";
    }
}

TokenType get_token_type(const char *token) {
    if (strcmp(token, "cmd") == 0) return TOKEN_CMD;
    if (strcmp(token, "arg") == 0) return TOKEN_ARG;
    if (strcmp(token, "SIMPLE_|") == 0) return TOKEN_PIPE;
    if (strcmp(token, "SIMPLE_>") == 0) return TOKEN_REDIR_OUT;
    if (strcmp(token, "fnm") == 0) return TOKEN_FNM;
    return TOKEN_UNKNOWN;
}

bool check_token_grammar()
{
    t_list *temp = _ms(0)->tokenized_prompt;
    State current_state = STATE_START;
    TokenType type;

    printf("Starting token grammar check\n");

    while (temp != NULL) {
        t_quote *quote = (t_quote *)temp->content;
        type = get_token_type(quote->token);
        
        printf("Token: %s, Content: %s, Type: %s, Current State: %s\n", 
               quote->token, quote->token, token_type_to_string(type), state_to_string(current_state));
        
        State next_state = transition_table[current_state][type];
        
        printf("Transitioning to state: %s\n", state_to_string(next_state));
        
        if (next_state == STATE_ERROR) {
            printf("Error encountered. Invalid transition.\n");
            return false;
        }
        
        current_state = next_state;
        temp = temp->next;
    }

    printf("Final state: %s\n", state_to_string(current_state));

    return (current_state == STATE_AFTER_CMD);
}