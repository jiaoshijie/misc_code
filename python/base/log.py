#! /usr/bin/python3
import logging
import math

# Create and configure logger
LOG_FORMAT = "%(levelname)s %(asctime)s  %(message)s"
logging.basicConfig(filename = "./.tmp/lumberjack.log", 
        level=logging.DEBUG, 
        format = LOG_FORMAT, 
        filemode = "w")
logger= logging.getLogger()

# Test the logger
# logger.info("My first message.")

#  logger.debug("This is harmless debug message.")
#  logger.info("Just some useful info.")
#  logger.warning("I'm sorry, but I can't do that, Dave")
#  logger.error("Did you just try to divide by zero?")
#  logger.critical("The entire internet is down!")

def quadratic_formula(a, b, c):
    logger.info("quadratic_formula({0}, {1}, {2})".format(a, b, c))

    logger.debug("# Compute the two discriminant")
    disc = b ** 2 - 4 * a * c

    logger.debug("# Compute the two roots")
    root1 = (-b + math.sqrt(disc) / (2 * a))
    root2 = (-b - math.sqrt(disc) / (2 * a))

    logger.debug("# return the roots")
    return (root1, root2)


roots = quadratic_formula(1, 0, -4)
