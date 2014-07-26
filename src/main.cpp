#include <iostream>

#include <pugihtml.hpp>


using namespace std;
namespace html = pugihtml;


string find_hello_world(const string& str_html);


int
main(void)
{
	const string str_xhtml =
	"<html>"
		"<body>"
			"<p>Hello world</p>"
		"</body>"
	"</html>"
	;
	cout << "Found in xhtml: " << find_hello_world(str_xhtml) << '\n';

	const string str_html =
	"<html>"
		"<body>"
			"<br>"
			"<p>Hello world</p>"
		"</body>"
	"</html>"
	;
	// This time it fails. pugihtml does not handle void html elements
	// which have only starting tag.
	cout << "Failed to find in html: " << find_hello_world(str_html) << '\n';

	html::html_document doc;
	doc.load(str_html.c_str());
	// This time <p> is considered inside <br>.
	cout << "Found in html: " << doc.child("HTML").child("BODY")
		.first_child().child("P").first_child().value() << '\n';

	return 0;
}


string
find_hello_world(const string& str_html)
{
	html::html_document doc;
	doc.load(str_html.c_str());

	// tag names are upper cased when parsing, but they are not when
	// querying for node. So we must use upper case to get the node.
	return doc.child("HTML").child("BODY").child("P").first_child()
		.value();
}
