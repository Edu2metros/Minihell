<h1 align="center"><strong>MINISHELL - @42SP</strong></h1>

<p align="center">
  <img src="https://github.com/Edu2metros/42-project-badges/blob/main/badges/minishelle.png?raw=true" alt="Minishell">
</p>

 <p align="center">Grade: <strong>91/100</strong> ✔️ </p>

This project involves creating a simple shell terminal.

The project includes a list of tasks to be completed. They are as follows:

## Execute simple commands and Built-ins:

### Built-ins:
- `echo`
- `cd`
- `env`
- `exit`
- `export`
- `pwd`
- `unset`

### Simple commands:
- `ls`
- `cat`
- `wc`
- `date`
- `grep`

## Redirections:
- Output: `ls > file`
- Append: `ls >> file`
- Input: `< file cat`
- Heredoc: `<< (delimiter) cat`

## Pipes:

```bash
< star_wars_script.txt cat | grep "I am your father!" | tr a-z A-Z >> file.txt
