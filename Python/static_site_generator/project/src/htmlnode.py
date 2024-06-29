class HTMLNode:
    def __init__(self, tag: str | None=None, 
                 value: str | None=None, 
                 children: list | None=None, 
                 props: dict[str, str] | None=None) -> None:
        self.tag = tag
        self.value = value
        self.children = children
        self.props = props
    def to_html(self):
        raise NotImplementedError
    def props_to_html(self) -> str:
        if(self.props == None):
            return ''
        string = ''
        props = self.props.copy()
        for k,v in props.items():
            string = f'{string} {k}="{v}"'
        return string
    def __repr__(self) -> str:
        return f'HTMLNode(\n tag:{self.tag}\n value:{self.value}\n children:{self.children}\n props:{self.props}\n)'
