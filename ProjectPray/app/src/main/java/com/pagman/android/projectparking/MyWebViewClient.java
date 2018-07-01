package com.pagman.android.projectparking;

import android.content.Intent;
import android.net.Uri;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import static android.os.Build.VERSION_CODES.M;

/**
 * Created by PagMan on 8/5/2017.
 */

private String Url = "http://stackoverflow.com";
class MyWebViewClient extends WebViewClient {
    @Override
    public boolean shouldOverrideUrlLoading(WebView view, String Url) {
        // This line right here is what you're missing.
        // Use the url provided in the method.  It will match the member URL!
        view.loadUrl(url);
        return true;
    }
}

}
