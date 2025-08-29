import cv2
cap = cv2.VideoCapture(0)  # Access laptop camera
while True:
   ret, frame = cap.read()
   if not ret:
       break

   # Display the camera feed
   cv2.imshow('Camera Feed', frame)

   # Send commands to Arduino based on keypress
   key = cv2.waitKey(1) & 0xFF
   if key == ord('1'):  # Press '1' to turn LED ON
       arduino.write(b'1')
   elif key == ord('0'):  # Press '0' to turn LED OFF
       arduino.write(b'0')
   elif key == ord('q'):  # Press 'q' to quit
       break

cap.release()
cv2.destroyAllWindows()
arduino.close()
