import unittest

from textnode import TextNode


class TestTextNode(unittest.TestCase):
    def test_eq(self):
        node = TextNode("This is a text node", "bold")
        node2 = TextNode("This is a text node", "bold")
        self.assertEqual(node, node2)
    def test_url_defaults_to_none(self):
        node = TextNode('This is text', 'bold')
        self.assertEqual(node.url, None)
    def test_repr_method(self):
        node = TextNode('This is text', 'bold', 'https://example.com')
        self.assertEqual(node.__repr__(), 'TextNode(This is text, bold, https://example.com)')
    def test_nodes_not_equal(self):
        node = TextNode('This text', 'bold', 'https://example.com')
        node2 = TextNode('This is text', 'bold', 'https://example.com')
        self.assertNotEqual(node, node2)



if __name__ == "__main__":
    unittest.main()
