

from game import Room, Game


def DFSUtil(game, temp, v, visited):
    # Mark the current vertex as visited
    visited[v.room_id] = True

    # Store the vertex to list
    temp.append(v.room_id)

    # Repeat for all vertices adjacent
    # to this vertex v
    for i in v.adjacent_rooms:
        if not visited[i.room_id]:
            # Update the list
            temp = DFSUtil(game,temp, i, visited)
    return temp
def count_good_dungeons(game: Game) -> int:
    """
    Fill out doc-string
    """
    visited = {}
    hash={}
    cc = []
    for i in game.rooms:
        visited[i.room_id]=False
        hash[i.room_id]=i
    # print(visited)
    for v in game.rooms:
        if not visited[v.room_id]:
            temp = []
            cc.append(DFSUtil(game,temp, v, visited))
            # print(v)
            
    # print (cc)
    
    count=0
    for x in cc:
        
        
        if len(x)>2:
            # print(x)
            # print()
            if hash[x[0]] in hash[x[len(x)-1]].adjacent_rooms:
                # print("here")
                # print(x)
                # print(hash[x[0]].room_id,hash[x[len(x)-1]].room_id)
                # print(hash[x[0]].adjacent_rooms)
                # print(hash[x[len(x)-1]].adjacent_rooms)
                count+=1
            else:
                for i in x:
                    # print(hash[i].room_id,len(hash[i].adjacent_rooms))
                    if(len(hash[i].adjacent_rooms)>2):
                        count+=1
                        break
       
    return count
