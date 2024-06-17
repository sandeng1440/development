from typing import Callable

def new_collection(initial_docs: list[str]) -> Callable[[str], list[str]]:
    docs: list[str] = initial_docs.copy()
    def inner_func(doc: str):
        nonlocal docs
        docs.append(doc)
        return docs
    return inner_func
