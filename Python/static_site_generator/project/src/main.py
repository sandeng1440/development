from textnode import TextNode

def main():
    node = TextNode('Hello world!', 'normal')
    print(f'{node.__repr__()}')

if __name__ == '__main__':
    main()
