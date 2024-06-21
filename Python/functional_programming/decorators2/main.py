
def markdown_to_text_decorator(func):
    def wrapper(*args, **kwargs):
        p_args: list[str]= list(map(convert_md_to_txt, [*args]))
        k_args: dict = {k: convert_md_to_txt(v) for k, v in kwargs.items()}
        return func(*p_args, **k_args)
    return wrapper

# don't touch below this line


def convert_md_to_txt(doc):
    lines = doc.split("\n")
    for i in range(len(lines)):
        line = lines[i]
        lines[i] = line.lstrip("# ")
    return "\n".join(lines)
