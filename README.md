# Contact_book

A beautified contact book management system built with Qt C++.

## Features

- **Modern UI**: Clean and professional interface with smooth animations
- **Contact Management**: Add, import, and export contact information
- **Animated Interactions**: 
  - Smooth fade-in effect when application starts (800ms)
  - Visual feedback when adding new contacts (green highlight animation)
  - Enhanced button interactions with hover and press animations
  - Focus effects on input fields for better UX
- **Data Persistence**: Save and load contact data from text files

## Animations

This application includes several smooth animations to enhance user experience:

1. **Window Fade-In**: The application window smoothly fades in when launched
2. **Row Insertion Highlight**: New contacts are highlighted briefly in green when added
3. **Button Feedback**: Buttons respond with subtle visual changes on hover and press
4. **Input Focus**: Text fields change background color when focused

## Building

This project uses Qt and requires:
- Qt 5 or higher
- C++17 support

```bash
qmake Contact_book.pro
make
```