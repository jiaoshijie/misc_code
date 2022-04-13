#! /usr/bin/python3
import logging
import time

logging.basicConfig(filename = "./.tmp/try.log", level= logging.DEBUG)
logger = logging.getLogger()

def read_file_timed(path):
    start_time = time.time()
    try:
        f = open(path, mode="rb")
        data = f.read()
        return data
    except FileNotFoundError as err:
        logger.error(err)
        raise
    else:
        f.close()
    finally:
        stop_time = time.time()
        dt = stop_time - start_time
        logger.info("Time required for {file} = {time}".format(file=path, time=dt))

if __name__ == "__main__":
    read_file_timed("/home/red/Downloads/manjaro-i3-18.1.0-stable-x86_64.iso")
