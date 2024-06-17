from typing import Callable, Union

def doc_format_checker_and_converter(
        conversion_function: Callable[[str], str], 
        valid_formats: list[str]) -> Callable[[str, str], Union[None, str]]:
    def inner_func(filename: str, content: str) -> str | None:
        if(filename.split('.')[-1] in valid_formats):
            return conversion_function(content)
        raise ValueError("Invalid file format")
    return inner_func


# Don't edit below this line


def capitalize_content(content: str) -> str:
    return content.upper()


def reverse_content(content: str) -> str:
    return content[::-1]
