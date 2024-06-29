import unittest

from htmlnode import HTMLNode

class TestHTMLNode(unittest.TestCase):
    def test_props_to_html(self):
        node = HTMLNode('a', 'Hello World', None, {"href": "https://www.google.com", "target": "_blank"})
        self.assertEqual(node.props_to_html(), ' href="https://www.google.com" target="_blank"')
    def test_empty_props(self):
        node = HTMLNode('p', 'Hello World')
        self.assertEqual(node.props_to_html(), '')
