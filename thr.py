from random import random
import threading
import time

result = None

def background_calculation():
    # here goes some long calculation
    time.sleep(random() * 5 * 60)

    # when the calculation is done, the result is stored in a global variable
    global result
    result = 42

    # do some more work before exiting the thread
    time.sleep(10)

def main():
    thread = threading.Thread(target=background_calculation)
    thread.start()

    # wait here for the result to be available before continuing
    thread.join()

    print('The result is', result)

if __name__ == '__main__':
    main()
