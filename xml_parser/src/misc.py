

def indent_strings(indent, string):
    def indent_f(line):
        return f"{indent}{line}"  if line else "" 
    
    return "\n".join([indent_f(line) for line in string.split("\n")])