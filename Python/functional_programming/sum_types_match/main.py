
from enum import Enum


class DocFormat(Enum):
    PDF = 1
    TXT = 2
    MD = 3
    HTML = 4


# don't touch above this line


def convert_format(content, from_format, to_format):
    match(from_format, to_format):
        case(DocFormat.MD, DocFormat.HTML):
            return '<h1>' + content.removeprefix('# ') + '</h1>'
        case(DocFormat.TXT, DocFormat.PDF):
            return '[PDF] ' + content + ' [PDF]'
        case(DocFormat.HTML, DocFormat.MD):
            return '# ' + content.removeprefix('<h1>').removesuffix('</h1>')
        case _:
            raise Exception('Invalid type')
