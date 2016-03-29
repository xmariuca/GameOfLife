#!/usr/bin/env python
from scipy.io import loadmat
import scipy.ndimage as scp
import matplotlib.animation
import matplotlib.pyplot
import numpy as np
def plot(frames,outpath):
    figure = matplotlib.pyplot.figure()
    def _animate(frame_id):
        print "Processing frame", frame_id
        matplotlib.pyplot.imshow(frames[frame_id,:,:], cmap="gray", vmin=0, vmax=1)

    anim = matplotlib.animation.FuncAnimation(figure, _animate, frames.shape[0], interval=100)
    anim.save(outpath)

with open('/Users/ucaHome/ClionProjects/GameOfLife/build/output.txt') as f:
    rows, cols = [int(x) for x in f.readline().split()]
    dataArr = []
    for line in f:
        data_line = [float(x) for x in line.split()]
#         print(data_line)
        if data_line:
            dataArr.append(data_line)

    npArr = np.array(dataArr)
    num_frames = npArr.shape[0]/rows
    npArr = npArr.reshape([num_frames,rows,cols])
    plot(npArr,'./vidGameOfLive.avi')
