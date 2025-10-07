// Banker's algorithm
// Deadlock avoidance and detection

#include<stdio.h>

int main() {
    int n,m; // no. of processes, no. of resources
    int i,j,k; // to iterate over loop
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("enter number of resources: ");
    scanf("%d",&m);
    
    int alloc[n][m];  // allocation matrix
    int max[n][m];  // max matrix
    int avail[m];  // available resources
    int need[n][m];  // need matrix
    
    // read allocation matrix
    printf("\nenter allocation matrix\n");
    for(i=0; i<n; i++) {
        printf("process p%d",i);
        for(j=0; j<m; j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    
    // read max matrix
    printf("\nenter max matrix\n");
    for(i=0; i<n; i++) {
        printf("process p%d",i);
        for(j=0; j<m; j++){
            scanf("%d",&max[i][j]);
        }
    }
    
    // read available matrix
    printf("\nenter available matrix\n");
    for(i=0; i<n; i++) {
        printf("process p%d",i);
        scanf("%d",&avail[i]);
    }
    
    // calc need matrix
    for(i=0; i<n; i++) {
        for(j=0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    //banker algorithm
    int f[n],ans[n], ind=0;
    for(k=0; k<n; k++) {
        f[k]=0;
    }
    
    for(k=0; k<n; k++) {
       for(i=0; i<n; i++) {
           if(f[i]==0) {
               int flag = 0;
               for(j=0; j<m; j++) {
                   if(need[i][j] > avail[j]){
                       flag=1;
                       break;
                   }
               }
               if(flag == 0) {
                   ans[ind++] = i;
                   for(j=0;j<m;j++) {
                       avail[j] += alloc[i][j];
                   }
                   f[i]=1;
               }
           }
       }
    }
    
// check if system is in safe state
  int flag = 1;
  for(i=0; i<n; i++) {
      if(f[i] == 0) {
          flag = 0;
          printf("\n system is not in safe state \n");
          break;
      }
  }
  
  if(flag == 1) {
      printf("\n system is in safe state \n");
      for(i=0; i<n; i++) {
          printf("p%d ->",ans[i]);
      }
      printf("p%d\n",ans[n-1]);
  }
   return 0; 
}
