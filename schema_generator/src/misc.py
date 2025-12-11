
new_line = "\n"

def indent_strings(indent, string):
    def indent_f(line):
        return f"{indent}{line}"  if line else "" 
    
    return "\n".join([indent_f(line) for line in string.split("\n")])


def format_schema_include(header: str) -> str:
    prefix = header.split("_", 1)[0].lower()
    return f"ssp4cpp/schema/{prefix}/{header}"