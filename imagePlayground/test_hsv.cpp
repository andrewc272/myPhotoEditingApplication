void ImageEditorFrame::UpdateImage()
{
    // Copy the original image to avoid modifying it directly
    adjustedImage = originalImage.Copy();

    // Get slider values
    float hue = hueSlider->GetValue() / 100.0;
    float saturation = saturationSlider->GetValue() / 100.0;
    float value = valueSlider->GetValue() / 100.0;

    std::cout << "Hue: " << static_cast<float>(hue) << ", "
                      << "Saturation: " << static_cast<float>(saturation) << ", "
                      << "Value: " << static_cast<float>(value) << std::endl;
        std::cout << "\n";

    for (int x = 0; x < adjustedImage.GetWidth(); x++){
    for (int y = 0; y < adjustedImage.GetHeight(); y++){

        // get rgb values
        float r = (float)adjustedImage.GetRed(x, y);
        float g = (float)adjustedImage.GetGreen(x, y);
        float b = (float)adjustedImage.GetBlue(x, y);

        //convert to hsv
        // get max
        float max = r;
        if ( g > max ) max = g;
        if ( b > max ) max = b;

        //get min
        float min = r;
        if ( g < min ) min = g;
        if ( b < min ) min = b;

        //get diff
        float diff = max - min;

        float v = max/255;

        float s = diff/max;

        float hue_360;
        if (diff == 0){
            hue_360 = 0;
        }
        else{
            if ( r == max ){
                hue_360 = 0 + 60*(g-b) / diff;
            }
            else if ( g == max ){
                hue_360 = 120 + 60*(b-r) / diff;
            }
            else{ // b == max
                hue_360 = 240 + 60*(r-g) / diff;
            }
        }
        if (hue_360 < 0){
            hue_360 = hue_360 + 360;
        }

        float h = hue_360/360;

        if (max == 0) {
            h = 0;
            s = 0;
            v = 0;
        }

        //hsv manipulation
        // h = hue;
        s = saturation;
        v = value;


        //hsv to rgb
        max = v;
        min = v - s * v;

        diff = max - min;

        float sixth = 1.0/6.0;

        int base_angle = 0;
        if (1.0/6.0 < h && h <= 3.0/6.0){
            base_angle = 120;
        }
        if ((3.0/6.0 < h) && (h <= 5.0/6.0)){
            base_angle = 240;
        }

        float mid = min;

        bool roatate_positive = false;
        if ((0 < h && h <= 1.0/6.0) || (2.0/6.0 < h && h <= 3.0/6.0) || (4.0/6.0 < h && h <= 5.0/6.0)){
            roatate_positive = true;
        }

        if (roatate_positive){
            mid = (h*360 - base_angle)*diff/60+min;
        }
        else{
            mid = (base_angle - h*360)*diff/60+min;
        }

        if (mid < min){
            mid = (base_angle - 360*(h-1))*diff/60+min;
        }

        min = min * 255;
        mid = mid * 255;
        max = max * 255;

        if (base_angle == 0){
            if (roatate_positive){
                r = max;
                g = mid;
                b = min;
            }
            else{
                r = max;
                g = min;
                b = mid;
            }
        }
        if (base_angle == 120){
            if (roatate_positive){
                r = min;
                g = max;
                b = mid;
            }
            else{
                r = mid;
                g = max;
                b = min;
            }
        }
        if (base_angle == 240){
            if (roatate_positive){
                r = mid;
                g = min;
                b = max;
            }
            else{
                r = min;
                g = mid;
                b = max;
            }
        }

        adjustedImage.SetRGB(x, y, r, g, b);
    }
    }

    // Update the displayed image
    //imageDisplay->SetBitmap(wxBitmap(adjustedImage));
    //Refresh(); // Redraw the frame
}