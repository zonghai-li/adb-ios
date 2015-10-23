# adb-ios
Android ADB on iOS

# Porting Details
- ADB host (client + server architecture) on the iOS host side. The ADB server uses port 5037 as would normally do.

- No USB supported

- ADB client exposes some essential methods for caller codes to integrate ADB functionalities.

- Application should include private/public key files in the application bundle (.ipa). The location and file name must be as this: 
 - [app-bundle-path]/android/adbkey 
 - [app-bundle-path]/android/adbkey.pub

# Code Snippet

<pre><code>

// initialize the AdbClient
_adb = [[AdbClient alloc] init];

...

// connect to a device
[_adb connect:@"10.0.1.223" didResponse:^(bool succ, NSString *result) {
  NSLog("%d : %@", succ, result); 
}];

//install apk
NSString *apkPath = [[NSBundle mainBundle] pathForResource:@"Term" ofType:@"apk"];
[_adb installApk:apkPath flags:ADBInstallFlag_Replace didResponse:^(bool succ, NSString *result) {
    NSLog("%d : %@", succ, result);       
}];

// some shell commands
[_adb shell:@"pm list packages" didResponse:^(bool succ, NSString *result) {
  //...
}];

</code></pre>


