
def file_type_aggregator(func_to_decorate):
    counts = {}

    def wrapper(doc, file_type):
        nonlocal counts

        if file_type not in counts:
            counts[file_type] = 0
        counts[file_type] += 1
        result = func_to_decorate(doc, file_type)

        return result, counts

    return wrapper


# don't touch above this line
@file_type_aggregator
def process_doc(doc: str, file_type: str) -> str:
    return f"Processing doc: '{doc}'. File Type: {file_type}"
