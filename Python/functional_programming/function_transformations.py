from typing import Callable, Optional

def get_logger(formatter: Callable[[str, str], str]):
    def logger(first: str, second: str) -> Callable[[str, str], str]:
        return formatter(first, second)
    return logger

# Don't edit below this line

def test(first: str, errors: list[str], formatter: Callable[[str, str], str]):
    print("Logs:")
    logger = get_logger(formatter)
    for err in errors:
        print(f"{logger(first, err)}")
    print("====================================")


def colon_delimit(first: str, second: str) -> str:
    return f"{first}: {second}"


def dash_delimit(first: str, second: str) -> str:
    return f"{first} - {second}"


def main():
    db_errors = [
        "out of memory",
        "cpu is pegged",
        "networking issue",
        "invalid syntax",
    ]
    test("Doc2Doc FATAL", db_errors, colon_delimit)

    mail_errors = [
        "email too large",
        "non alphanumeric symbols found",
    ]
    test("Doc2Doc WARNING", mail_errors, dash_delimit)


main()
