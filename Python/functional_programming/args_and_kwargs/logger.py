
def args_logger(*args, **kwargs):
    for i in range(len(args)):
        print(f'{i + 1}. {args[i]}')
    for key, val in sorted(kwargs.items()):
        print(f'* {key}: {val}')
