from sense_hat import SenseHat

if __name__ == '__main__':
        sense = SenseHat()
        print(sense)
        print(type(sense))

        sense.show_message("192.168.5.8")
        sense.show_letter("z")

        temperature = sense.get_temperature()
        print(f"temperature:{temperature}")

        temperature = sense.get_temperature_from_humidity()
        print(f"temperature:{temperature}")

        temperature = sense.get_temperature_from_pressure()
        print(f"temperature:{temperature}")

#;;; Local Variables: ***
#;;; mode:python ***
#;;; End: ***
