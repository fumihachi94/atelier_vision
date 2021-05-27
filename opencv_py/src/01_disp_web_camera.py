import cv2

cap = cv2.VideoCapture(0)
assert cap.isOpened(), 'Can not open video device'

print(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
print(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

window_name = 'frame'

while True:
    ret, frame = cap.read()
    if ret:
        cv2.imshow(window_name, frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

cv2.destroyWindow(window_name)


