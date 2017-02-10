 #if defined(define1) && defined(define2)
 
 #include <read_database.h>
 
 int main()
-{
   #ifdef COVTOOL_INST
-    extern void CvT_StartRecording____();
-    CvT_StartRecording____();
   #endif
 
+  cout << "test1 is running";
+  cout << I_STRING << endl;
 
 
 }
 
 #endif
 
