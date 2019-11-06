function Component()
{
  // default constructor
}

Component.prototype.createOperations = function()
{
  component.createOperations();

  if (systemInfo.productType ==  "windows")
  {
    component.addOperation("Execute","{0,3010}","@TargetDir@/VC_redist.x64.exe","/quiet","/norestart");
    component.addOperation("CreateShortcut",
                   "@TargetDir@/image_view.exe",
                   "@StartMenuDir@/image_view.lnk",
                   "iconPath=@TargetDir@/image_view.ico")
    component.addOperation("CreateShortcut",
                   "@TargetDir@/image_view.exe",
                   "@DesktopDir@/image_view.lnk",
                   "iconPath=@TargetDir@/image_view.ico")
    component.addOperation("RegisterFileType",
                   ".cjpg",
                   "@TargetDir@/image_view.exe '%1'",
                   "Custom JPG file extension",
                   "text/plain",
                   "@TargetDir@/cjpg_file_icon.ico")
  }
}