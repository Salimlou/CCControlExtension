/*
 * CCControlPicker.h
 *
 * Copyright 2013 Yannick Loriot. All rights reserved.
 * http://yannickloriot.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#import "CCControl.h"

/**
 * Swipe orientation.
 */
typedef enum
{
    CCControlPickerOrientationVertical,
    CCControlPickerOrientationHorizontal
} CCControlPickerOrientation;

@protocol CCControlPickerDataSource;
@protocol CCControlPickerDelegate;

/**
 * Picker control for Cocos2D.
 *
 * The CCControlPicker class implements objects, called picker controls, that
 * use a spinning-wheel or slot-machine metaphor to show one set of values.
 * Users select values by rotating the wheels so that the desired row of values
 * aligns with a selection indicator.
 */
@interface CCControlPicker : CCControl <UIGestureRecognizerDelegate>

#pragma mark Contructors - Initializers
/** @name Create Pickers */

/** Initializes a picker the foreground and the selection sprite. */
- (id)initWithForegroundSprite:(CCSprite *)foregroundSprite selectionSprite:(CCSprite *)selectionSprite;

#pragma mark - Public Methods

#pragma mark Getting the Dimensions of the Control Picker
/** @name Getting the Dimensions of the Control Picker */
/**
 * @abstract Returns the size of a row.
 * @return The size of rows.
 * @discussion A picker control fetches the value of this property by
 * calling the rowHeightInControlPicker: delegate methods, and caches
 * it. The default value is CCControlPickerDefaultRowHeight.
 */
- (CGSize)rowSize;

/**
 * @abstract Returns the number of rows.
 * @return The number of rows.
 * @discussion A picker control fetches the value of this property
 * from the data source and and caches it. The default value is zero.
 */
- (NSUInteger)numberOfRows;

#pragma mark Reloading the Control Picker
/** @name Reloading the Control Picker */

/**
 * Reloads the component of the picker control.
 */
- (void)reloadComponent;

#pragma mark Selecting Rows in the Control Picker
/** @name Selecting Rows in the Control Picker */

/**
 * Selects a row in the picker control.
 * @param row A zero-indexed number identifying a row of component.
 * @param animated YES to animate the selection by spinning the wheel
 * (component) to the new value; if you specify NO, the new selection
 * is shown immediately.
 */
- (void)selectRow:(NSInteger)row animated:(BOOL)animated;

/**
 * Returns the index of the selected row.
 * @return A zero-indexed number identifying the selected row , or -1 
 * if no row is selected.
 * @see selectRow:animated:
 */
- (NSInteger)selectedRow;

#pragma mark Managing the Behavior of the Control Picker
/** @name Managing the Behavior of the Control Picker */

/**
 * @abstract The swipe orientation of the picker.
 * @discussion The orientation constrains the swipe direction.
 * E.g if the orientation is set to CCControlPickerOrientationVertical
 * the element can move in vertical only.
 * 
 * The default value for this property is CCControlPickerOrientationVertical.
 */
@property (nonatomic, assign) CCControlPickerOrientation swipeOrientation;

/**
 * @abstract The looping vs. nonlooping state of the picker.
 * @discussion If YES, the picker will display the data source as a
 * loop. I.e that when the end of the source is reached the picker
 * will display the first element.
 *
 * The default value for this property is NO.
 */
@property (nonatomic, getter = isLooping) BOOL looping;

#pragma mark Specifying the Delegate
/** @name Specifying the Delegate */
/**
 * @abstract The delegate for the control picker.
 * @discussion The delegate must adopt the CCControlPickerDelegate protocol
 * and implement the required methods to respond to new selections or
 * deselections.
 */
@property(nonatomic, assign) id<CCControlPickerDelegate> delegate;

#pragma mark Specifying the Data Source
/** @name Specifying the Data Source */
/**
 * @abstract The data source for the control picker.
 * @discussion The data source must adopt the CCControlPickerDataSource
 * protocol and implement the required methods to return the number of
 * rows in each component.
 */
@property(nonatomic, assign) id<CCControlPickerDataSource> dataSource;

@end

#pragma mark - CCControlPickerDataSource

/**
 * The CCControlPickerDataSource protocol must be adopted by an object
 * that mediates between a CCControlPicker object and your application’s
 * data model for that control picker. The data source provides the control
 * picker with the number of components, and the number of rows in the
 * component, for displaying the control picker data.
 * Both methods in this protocol are required.
 */
@protocol CCControlPickerDataSource <NSObject>

@required

/** @name Providing Counts for the Control Picker */

/**
 * Called by the picker control when it needs the number of rows. (required)
 * @param pickerControl The picker control requesting the data.
 * @return The number of rows.
 */
- (NSUInteger)numberOfRowsInPickerControl:(CCControlPicker *)pickerControl;

/** @name Setting the Content of Component Rows */

/**
 * Called by the picker control when it needs the title to use for a given row.
 * @param pickerControl An object representing the picker control requesting
 * the data.
 * @param row A zero-indexed number identifying a row of component. Rows are
 * numbered top-to-bottom.
 * @return The string to use as the title of the indicated row.
 */
- (NSString *)pickerControl:(CCControlPicker *)pickerControl titleForRow:(NSUInteger)row;

@end

#pragma mark - CCControlPickerDelegate

/**
 * The delegate of a CCControlPicker object must adopt this protocol and
 * implement at least some of its methods to provide the control picker with
 * the data it needs to construct itself.
 *
 * Typically the delegate implements optional methods to respond to new 
 * selections or deselections of component rows.
 *
 * See CCControlPicker Class Reference for a discussion of components, rows,
 * row content, and row selection.
 */
@protocol CCControlPickerDelegate <NSObject>
@end;