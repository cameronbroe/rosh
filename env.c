#include "env.h"
#include <unistd.h>

// Implement all of the appropriate functions for the environment

void load_env(shell_env *env, char* filename) {
	env->pwd = getcwd(NULL, 0);
	env->prompt = "rosh $ ";
	env->path = "/usr/local/heroku/bin:/home/cameron/.rvm/gems/ruby-2.1.2/bin:/home/cameron/.rvm/gems/ruby-2.1.2@global/bin:/home/cameron/.rvm/rubies/ruby-2.1.2/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/cameron/.rvm/bin:/home/cameron/.rvm/bin:/home/cameron/.rvm/bin";
}