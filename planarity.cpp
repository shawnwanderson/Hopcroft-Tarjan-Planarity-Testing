





bool planarity(graph G){
    int E = 0;
    for(auto v : G){
        E += v.size();
    }
    E = E/2;
    if(E > 3*V - 3){
        return false;
    }
    vector<graph> BC;
    biconnectedComponents(G, BC);
    
    for(auto C : BC){
        palm P = transform(C);
        cycle c = getCycle(P);
        planar plane = constructPlanar(c);
        vector<graph> pieces = delCycle(c, plane);
        for(auto piece : pieces){
            if(planarity(piece)){
                addPiece(piece);
            }
            else{
                return false;
            }
        }
    }
}
