import re

def filter_text_with_regex(input_text, regex_pattern):
    filtered_text = re.findall(regex_pattern, input_text)
    return ' '.join(filtered_text)

if __name__ == '__main__':
    input_text = input("Enter the text: ")
    regex_pattern = input("Enter the regular expression: ")

    try:
        filtered_text = filter_text_with_regex(input_text, regex_pattern)
        print("Filtered text:")
        print(filtered_text)
    except re.error:
        print("Invalid regular expression pattern.")

#%%
