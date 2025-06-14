import os
import ast

def parse_file(filepath):
    with open(filepath, 'r') as f:
        tree = ast.parse(f.read(), filepath)
    funcs = [node.name for node in ast.walk(tree) if isinstance(node, ast.FunctionDef)]
    classes = [node.name for node in ast.walk(tree) if isinstance(node, ast.ClassDef)]
    return funcs, classes

def generate_skeleton(root_dir):
    md = "# Project Skeleton\n\n"
    for root, dirs, files in os.walk(root_dir):
        level = root.replace(root_dir, '').count(os.sep)
        indent = '  ' * level
        md += f"{indent}- **{os.path.basename(root)}/**\n"
        for f in files:
            if f.endswith('.py'):
                funcs, classes = parse_file(os.path.join(root, f))
                md += f"{indent}  - {f}\n"
                if classes:
                    md += f"{indent}    - Classes:\n"
                    for c in classes:
                        md += f"{indent}      - {c}\n"
                if funcs:
                    md += f"{indent}    - Functions:\n"
                    for fn in funcs:
                        md += f"{indent}      - {fn}\n"
    return md

if __name__ == "__main__":
    skeleton_md = generate_skeleton(".")
    with open("skeleton.md", "w") as f:
        f.write(skeleton_md)
    print("skeleton.md generated!")
