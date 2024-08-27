# Ensure tDOM package is available
package require tdom

# Define the file path
set file_path "./proj_calcMatrixRhth/solution1/syn/report/csynth.xml"

# Open the file and read its contents
set file [open $file_path r]
set content [read $file]
close $file

# Parse the XML content
set doc [dom parse $content]

# Define the XPath expression to search for the specific hierarchy item
# For example, to search for an item with a specific tag and attribute
# Replace 'HierarchyItem' with the actual tag name and 'attribute' with the actual attribute name
set xpath_expression "//profile//AreaEstimates//Resources//LUT"

# Execute the XPath query
set nodes [$doc selectNodes $xpath_expression]

# Initialize a variable to hold the first node value
set first_node_value 0

# Check if any nodes were found
if {[llength $nodes] > 0} {
    # Get the first node
    set first_node [lindex $nodes 0]
    
    # Extract the text content of the first node
    set first_node_text [$first_node text]
    
    # Convert the text content to an integer
    set first_node_value [expr {$first_node_text + 0}]
    
    # Print the integer value
    puts $first_node_value
} else {
    puts "No matching hierarchy item found."
}

# Clean up
$doc delete

# Return the integer value to the outer function
return $first_node_value