
new_line = "\n"

def indent_strings(indent, string):
    def indent_f(line):
        return f"{indent}{line}" if line else "" 
    
    return "\n".join([indent_f(line) for line in string.split("\n")])

def join_indent(l : list[str], indent):
    l_s = "\n".join(l)
    return indent_strings(indent, l_s)


def format_schema_include(header: str) -> str:
    prefix = header.split("_", 1)[0].lower()
    return f"ssp4cpp/schema/{prefix}/{header}"