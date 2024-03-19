import sys
import math

def dbm_to_mw(dbm):
    return 10**(dbm / 10)

def mw_to_dbm(mw):
    return 10 * math.log10(mw)

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <value> <unit>")
        print("Example: python script.py -20 dBm")
        print("         python script.py 1 mW")
        sys.exit(1)

    value = float(sys.argv[1])
    unit = sys.argv[2].lower()

    if unit == 'dbm':
        converted_mw = dbm_to_mw(value)
        print(f'{value} dBm is equal to {converted_mw:.4f} mW')
    elif unit == 'mw':
        converted_dbm = mw_to_dbm(value)
        print(f'{value} mW is equal to {converted_dbm:.4f} dBm')
    else:
        print("Invalid unit. Please use 'dBm' or 'mW'.")

if __name__ == "__main__":
    main()
