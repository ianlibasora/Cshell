https://stackoverflow.com/questions/33508997/waitpid-wnohang-wuntraced-how-do-i-use-these/34845669

Note:
- Background operation handled by double fork
- Main process forks to give `Parent`, `Child`
- `Child` forks to give `Child-Child`, `Child-Parent`
- `Child-Parent` immediately dies and sends it returncode to `Parent`
- `Parent` recieves `Child-Parent's` return code,allowing it to detach, while `Child-Child` runs the taskin background until it finishes execution

Ref: https://askubuntu.com/questions/857993how-to-kill-zombie-process-keeping-its-parent-alive
