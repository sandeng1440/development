import unittest

from htmlnode import HTMLNode, LeafNode

class TestHTMLNode(unittest.TestCase):
    def test_props_to_html(self):
        node = HTMLNode('a', 'Hello World', None, {"href": "https://www.google.com", "target": "_blank"})
        self.assertEqual(node.props_to_html(), ' href="https://www.google.com" target="_blank"')
    def test_empty_props(self):
        node = HTMLNode('p', 'Hello World')
        self.assertEqual(node.props_to_html(), '')

class TestLeafNode(unittest.TestCase):
    def test_leaf_node_to_html(self):
        leaf = LeafNode("p", "This is a paragraph of text.")
        leaf2 = LeafNode("a", "Click me!", {"href": "https://www.google.com"})
        self.assertEqual(leaf.to_html(), '<p>This is a paragraph of text.</p>')
        self.assertEqual(leaf2.to_html(), '<a href="https://www.google.com">Click me!</a>')
