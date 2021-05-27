import open3d as o3d
import numpy as np

pcd = o3d.io.read_point_cloud("../model/scene_dense.ply")
print(pcd)
print(np.asarray(pcd.points))
downpcd = pcd.voxel_down_sample(voxel_size=0.03)
downpcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=0.04, max_nn=10))


o3d.visualization.draw_geometries([pcd], point_show_normal=False)
