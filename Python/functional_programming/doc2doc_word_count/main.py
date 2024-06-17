def word_count_aggregator():
    count: int = 0
    def inner_func(doc: str):
        nonlocal count
        count += len(doc.split(" "))
        return count
    return inner_func
