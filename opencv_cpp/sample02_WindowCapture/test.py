import cv2

WINDOW_ID = '0x2800018'  # さっき確認したID

video = cv2.VideoCapture(f'ximagesrc xid={WINDOW_ID} ! videoconvert ! appsink')

while cv2.waitKey(1) != 27:
    ok, img = video.read()
    if not ok:
        print("Error brank")
        break
    cv2.imshow('test', img)