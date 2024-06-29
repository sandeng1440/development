class TextNode:
    def __init__(self, text, text_type, url=None) -> None:
        self.text: str = text
        self.text_type: str = text_type
        self.url: str | None = url
    def __eq__(self, other) -> bool:
        if(isinstance(other, TextNode)):
            return self.text == other.text and self.text_type == other.text_type and self.url == other.url
        return False
    def __repr__(self) -> str:
        return f'TextNode({self.text}, {self.text_type}, {self.url})'
