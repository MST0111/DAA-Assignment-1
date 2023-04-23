import matplotlib.pyplot as plt
 
f=open("merge.txt")
n=int(f.readline())
 
el=[]
vrt = []
 
for line in range(n):
    p,q,r,s = (f.readline()).split(" ")
    p = float(p)
    q = float(q)
    r = float(r)
    s = float(s)
    el.append(((p,q),(r,s)))
    vrt.append((p,q))
    vrt.append((r,s))
 
vrt = list(set(vrt))
 
 
fig,ax = plt.subplots()
 
 
for p1,p2 in el:
    x1,y1 = p1
    x2,y2 = p2
    ax.plot([x1,x2],[y1,y2],color='g')
 
ax.set_xlim(min([x[0] for x in vrt  ] )-5,max([x[0] for x in vrt ])+5)
ax.set_ylim(min([x[1] for x in vrt  ])-5,max([x[1] for x in vrt] )+5)
 
# plt.annotate('Label', xy=(1, 2), xytext=(1.5, 3),
#              arrowprops=dict(facecolor='black', shrink=0.05))
 
# for i,j in vrt:
#     plt.text(i,j,'({},{})'.format(i,j),fontsize=6)
 
plt.show()