from collections.abc import Callable
from functools import reduce

def lines_with_sequence(char: str) -> Callable[[int], Callable[[str], int]]:
    def with_char(length: int) -> Callable[[str], int]:
        sequence: str = char * length
        def with_length(doc: str) -> int:
            lines: list[str] = doc.split('\n')
            return reduce(lambda x, y: x+1 if sequence in y else x, lines, 0)
        return with_length
    return with_char
