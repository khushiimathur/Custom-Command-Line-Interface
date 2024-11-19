out/bish: out/list out/date out/display out/make_dir out/remove_dir src/shell.c
	@mkdir -p out
	@gcc -pthread -o out/shell src/shell.c
	@echo "\nComplied the shell \n"
	@echo "To get the help regarding the commands of the shell refer to README.md\n"
	@echo "Run ./out/shell to start the shell"
	@echo "Or use 'make run' to run the shell\n"

out/list: src/list.c
	@mkdir -p out
	@gcc -o out/list src/list.c
	@echo "Compiled list"


out/date: src/date.c
	@mkdir -p out
	@gcc -o out/date src/date.c
	@echo "Compiled date"

out/display: src/display.c
	@mkdir -p out
	@gcc -o out/display src/display.c
	@echo "Compiled display"

out/make_dir: src/make_dir.c
	@mkdir -p out
	@gcc -o out/make_dir src/make_dir.c
	@echo "Compiled make_dir"

out/remove_dir: src/remove_dir.c
	@mkdir -p out
	@gcc -o out/remove_dir src/remove_dir.c
	@echo "Compiled remove_dir"
	
out/convert: src/convert.c
	@mkdir -p out
	@gcc -o out/convert src/convert.c
	@echo "Compiled convert"

clean:
	@rm -rf out
	@echo "Cleaned the executables"

run: out/shell
	@./out/shell
	